/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "./FileReader.h"
#include "./HttpConnection.h"
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpServer.h"
#include "./libhw3/QueryProcessor.h"

using std::cerr;
using std::cout;
using std::endl;

namespace hw4 {

// This is the function that threads are dispatched into
// in order to process new client connections.
void HttpServer_ThrFn(ThreadPool::Task *t);

// Given a request, produce a response.
HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices);

// Process a file request.
HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir);

// Process a query request.
HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices);

bool HttpServer::Run(void) {
  // Create the server listening socket.
  int listen_fd;
  cout << "  creating and binding the listening socket..." << endl;
  if (!ss_.BindAndListen(AF_INET6, &listen_fd)) {
    cerr << endl << "Couldn't bind to the listening socket." << endl;
    return false;
  }

  // Spin, accepting connections and dispatching them.  Use a
  // threadpool to dispatch connections into their own thread.
  cout << "  accepting connections..." << endl << endl;
  ThreadPool tp(kNumThreads);
  while (1) {
    HttpServerTask *hst = new HttpServerTask(HttpServer_ThrFn);
    hst->basedir = staticfile_dirpath_;
    hst->indices = &indices_;
    if (!ss_.Accept(&hst->client_fd,
                    &hst->caddr,
                    &hst->cport,
                    &hst->cdns,
                    &hst->saddr,
                    &hst->sdns)) {
      // The accept failed for some reason, so quit out of the server.
      // (Will happen when kill command is used to shut down the server.)
      break;
    }
    // The accept succeeded; dispatch it.
    tp.Dispatch(hst);
  }
  return true;
}

void HttpServer_ThrFn(ThreadPool::Task *t) {
  // Cast back our HttpServerTask structure with all of our new
  // client's information in it.
  std::unique_ptr<HttpServerTask> hst(static_cast<HttpServerTask *>(t));
  cout << "  client " << hst->cdns << ":" << hst->cport << " "
       << "(IP address " << hst->caddr << ")" << " connected." << endl;

  bool done = false;
  while (!done) {
    // Use the HttpConnection class to read in the next request from
    // this client, process it by invoking ProcessRequest(), and then
    // use the HttpConnection class to write the response.  If the
    // client sent a "Connection: close\r\n" header, then shut down
    // the connection.

    // Done:
    bool res0, res1;
    HttpRequest hreq;
    HttpResponse hrep;
    HttpConnection hc(hst->client_fd);
    res0 = hc.GetNextRequest(&hreq);
    hrep = ProcessRequest(hreq, hst->basedir, hst->indices);
    res1 = hc.WriteResponse(hrep);
    if (!res0 || !res1 ||  (hreq.headers["connection"] == "close")) {
      close(hst->client_fd);
      done = true;
    }
  }
}

HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices) {
  // Is the user asking for a static file?
  if (req.URI.substr(0, 8) == "/static/") {
    return ProcessFileRequest(req.URI, basedir);
  }

  // The user must be asking for a query.
  return ProcessQueryRequest(req.URI, indices);
}


HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir) {
  // The response we'll build up.
  HttpResponse ret;

  // Steps to follow:
  //  - use the URLParser class to figure out what filename
  //    the user is asking for.
  //
  //  - use the FileReader class to read the file into memory
  //
  //  - copy the file content into the ret.body
  //
  //  - depending on the file name suffix, set the response
  //    Content-type header as appropriate, e.g.,:
  //      --> for ".html" or ".htm", set to "text/html"
  //      --> for ".jpeg" or ".jpg", set to "image/jpeg"
  //      --> for ".png", set to "image/png"
  //      etc.
  //
  // be sure to set the response code, protocol, and message
  // in the HttpResponse as well.
  std::string fname = "";
  // DONE:
  URLParser p;
  p.Parse(uri);
  string path = p.get_path();
  fname += path;
  if (path.find("/static/") == 0) {
    fname = path.substr(8, path.size());
  }
  FileReader reader(basedir, fname);
  if (reader.ReadFile(&ret.body)) {
    std::string suffix = fname.substr(fname.rfind("."), fname.length() - 1);
    if (suffix == ".html" || suffix == ".htm") {
      ret.headers["Content-type"] = "text/html";
    } else if (suffix == ".jpeg" || suffix == ".jpg") {
      ret.headers["Content-type"] = "image/jpeg";
    } else if (suffix == ".png") {
      ret.headers["Content-type"] = "image/png";
    } else if (suffix == ".7z") {
      ret.headers["Content-type"] = "application/x-7z-compressed";
    } else if (suffix == ".aab") {
      ret.headers["Content-type"] = "application/x-authorware-bin";
    } else if (suffix == ".aam") {
      ret.headers["Content-type"] = "application/x-authorware-map";
    } else if (suffix == ".aas") {
      ret.headers["Content-type"] = "application/x-authorware-seg";
    } else if (suffix == ".air") {
      ret.headers["Content-type"] =
      "application/vnd.adobe.air-application-installer-package+zip";
    } else if (suffix == ".swf") {
      ret.headers["Content-type"] = "application/x-shockwave-flash";
    } else if (suffix == ".pdf") {
      ret.headers["Content-type"] = "application/pdf";
    } else if (suffix == ".xdp") {
      ret.headers["Content-type"] = "application/vnd.adobe.xdp+xml";
    } else if (suffix == ".xfdf") {
      ret.headers["Content-type"] = "application/vnd.adobe.xfdf";
    } else if (suffix == ".aac") {
      ret.headers["Content-type"] = "audio/x-aac";
    } else if (suffix == ".azw") {
      ret.headers["Content-type"] = "application/vnd.amazon.ebook";
    } else if (suffix == ".apk") {
      ret.headers["Content-type"] = "application/vnd.android.package-archive";
    } else if (suffix == ".dmg") {
      ret.headers["Content-type"] = "application/x-apple-diskimage";
    } else if (suffix == ".mpkg") {
      ret.headers["Content-type"] = "application/vnd.apple.installer+xml";
    } else if (suffix == ".s") {
      ret.headers["Content-type"] = "text/x-asm";
    } else if (suffix == ".aif") {
      ret.headers["Content-type"] = "audio/x-aiff";
    } else if (suffix == ".avi") {
      ret.headers["Content-type"] = "video/x-msvideo";
    } else if (suffix == ".torrent") {
      ret.headers["Content-type"] = "application/x-bittorrent";
    } else if (suffix == ".sh") {
      ret.headers["Content-type"] = "application/x-sh";
    } else if (suffix == ".csh") {
      ret.headers["Content-type"] = "application/x-csh";
    } else if (suffix == ".c") {
      ret.headers["Content-type"] = "text/x-c";
    } else if (suffix == ".css") {
      ret.headers["Content-type"] = "text/css";
    } else if (suffix == ".csv") {
      ret.headers["Content-type"] = "text/csv";
    } else if (suffix == ".deb") {
      ret.headers["Content-type"] = "application/x-debian-package";
    } else if (suffix == ".djvu") {
      ret.headers["Content-type"] = "image/vnd.djvu";
    } else if (suffix == ".eml") {
      ret.headers["Content-type"] = "message/rfc822";
    } else if (suffix == ".xif") {
      ret.headers["Content-type"] = "image/vnd.xiff";
    } else if (suffix == ".f4v") {
      ret.headers["Content-type"] = "video/x-f4v";
    } else if (suffix == ".flv") {
      ret.headers["Content-type"] = "video/x-flv";
    } else if (suffix == ".f") {
      ret.headers["Content-type"] = "text/x-fortran";
    } else if (suffix == ".fh") {
      ret.headers["Content-type"] = "image/x-freehand";
    } else if (suffix == ".gif") {
      ret.headers["Content-type"] = "image/gif";
    } else if (suffix == ".h261") {
      ret.headers["Content-type"] = "video/h261";
    } else if (suffix == ".h263") {
      ret.headers["Content-type"] = "video/h263";
    } else if (suffix == ".h264") {
      ret.headers["Content-type"] = "video/h264";
    } else if (suffix == ".ics") {
      ret.headers["Content-type"] = "text/calendar";
    } else if (suffix == ".ico") {
      ret.headers["Content-type"] = "image/x-icon";
    } else if (suffix == ".ief") {
      ret.headers["Content-type"] = "image/ief";
    } else if (suffix == ".igs") {
      ret.headers["Content-type"] = "model/iges";
    } else if (suffix == ".java") {
      ret.headers["Content-type"] = "text/x-java-source,java";
    } else if (suffix == ".js") {
      ret.headers["Content-type"] = "application/javascript";
    } else if (suffix == ".json") {
      ret.headers["Content-type"] = "application/json";
    } else if (suffix == ".jpm") {
      ret.headers["Content-type"] = "video/jpm";
    } else if (suffix == ".jpgv") {
      ret.headers["Content-type"] = "video/jpeg";
    } else if (suffix == ".m4v") {
      ret.headers["Content-type"] = "video/x-m4v";
    } else if (suffix == ".exe") {
      ret.headers["Content-type"] = "application/x-msdownload";
    } else if (suffix == ".pptx") {
      ret.headers["Content-type"] =
    "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    } else if (suffix == ".xlsx") {
      ret.headers["Content-type"] =
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    } else if (suffix == ".docx") {
      ret.headers["Content-type"] =
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    } else if (suffix == ".txt") {
      ret.headers["Content-type"] = "text/plain";
    } else if (suffix == ".tif" || suffix == ".tiff") {
      ret.headers["Content-type"] = "image/tiff";
    } else {
      ret.headers["Content-type"] = "application/octet-stream";
    }
    ret.protocol = "HTTP/1.1";
    ret.response_code = 200;
    ret.message = "OK";
    return ret;
  }
  // If you couldn't find the file, return an HTTP 404 error.
  ret.protocol = "HTTP/1.1";
  ret.response_code = 404;
  ret.message = "Not Found";
  ret.body = "<html><body>Couldn't find file \"";
  ret.body +=  EscapeHTML(fname);
  ret.body += "\"</body></html>";
  return ret;
}

HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices) {
  // The response we're building up.
  HttpResponse ret;

  // Your job here is to figure out how to present the user with
  // the same query interface as our solution_binaries/http333d server.
  // A couple of notes:
  //
  //  - no matter what, you need to present the 333gle logo and the
  //    search box/button
  //
  //  - if the user had previously typed in a search query, you also
  //    need to display the search results.
  //
  //  - you'll want to use the URLParser to parse the uri and extract
  //    search terms from a typed-in search query.  convert them
  //    to lower case.
  //
  //  - you'll want to create and use a hw3::QueryProcessor to process
  //    the query against the search indices
  //
  //  - in your generated search results, see if you can figure out
  //    how to hyperlink results to the file contents, like we did
  //    in our solution_binaries/http333d.

  // DONE:
  ret.body = "<html><head><title>333gle</title></head>\r\n";
  ret.body += "<body>\r\n";
  ret.body += "<center style=\"font-size:500%;\">\r\n";
  ret.body += "<span style=\"position:relative;bottom:-0.33em;";
  ret.body += "color:orange;\">3</span>";
  ret.body += "<span style=\"color:red;\">3</span>";
  ret.body += "<span style=\"color:gold;\">3</span>";
  ret.body += "<span style=\"color:blue;\">g</span>";
  ret.body += "<span style=\"color:green;\">l</span>";
  ret.body += "<span style=\"color:red;\">e</span>\r\n";
  ret.body += "</center>\r\n";
  ret.body += "<p>\r\n";
  ret.body += "<div style=\"height:20px;\"></div>\r\n";
  ret.body += "<center>\r\n";
  ret.body += "<form action=\"/query\" method=\"get\">\r\n";
  ret.body += "<input type=\"text\" size=30 name=\"terms\" />\r\n";
  ret.body += "<input type=\"submit\" value=\"Search\" />\r\n";
  ret.body += "</form>\r\n";
  ret.body += "</center><p>\r\n";
  ret.protocol = "HTTP/1.1";
  ret.response_code = 200;
  ret.message = "OK";
  // parse the uri and get query
  URLParser p;
  p.Parse(uri);
  std::string query = p.get_args()["terms"];
  boost::trim(query);
  // convert to lower case
  boost::to_lower(query);
  // initial state when user first uses broswer
  if (uri.find("query?terms=") == std::string::npos) {
    ret.body += "</body>\r\n";
    ret.body += "</html>\r\n";
    return ret;
  }
  std::vector<std::string> qvec;
  boost::split(qvec, query, boost::is_any_of(" "), boost::token_compress_on);
  hw3::QueryProcessor qp(*indices, false);
  std::vector<hw3::QueryProcessor::QueryResult> qr = qp.ProcessQuery(qvec);
  // check if we found the result
  // if not display nothing
  if (qr.size() == 0) {
    ret.body += "<p><br>\r\n";
    ret.body += "No results found for <b>";
    ret.body += EscapeHTML(query);
    ret.body += "</b>\r\n";
    ret.body += "<p>\r\n";
    ret.body += "\r\n";
  } else {
    // if we found the result, show the results with its rank
    std::stringstream ss;
    ret.body += "<p><br>\r\n";
    ss << qr.size();
    ret.body += ss.str();
    ss.str("");
    ret.body += " result";
    // if it has more than 1 result
    if (qr.size() != 1) {
      ret.body += "s ";
    } else {
      ret.body += " ";
    }
    ret.body += "found for <b>";
    ret.body += EscapeHTML(query);
    ret.body += "</b>\r\n";
    ret.body += "<p>\r\n\r\n";
    // display result with hyperlink
    ret.body += "<ul>\r\n";
    for (auto element : qr) {
      ret.body += " <li> <a href=\"";
      // add static
      if (element.document_name.substr(0, 7) != "http://") {
        ret.body += "/static/";
      }
      ret.body += element.document_name;
      ret.body += "\">";
      ret.body += EscapeHTML(element.document_name);
      ret.body += "</a>";
      ret.body += " [";
      ss << element.rank;
      ret.body += ss.str();
      ss.str("");
      ret.body += "]<br>\r\n";
    }
    ret.body += "</ul>\r\n";
  }
  ret.body += "</body>\r\n";
  ret.body += "</html>\r\n";
  return ret;
}
}  // namespace hw4
