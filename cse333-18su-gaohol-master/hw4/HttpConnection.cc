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

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::vector;
using std::string;
using namespace boost;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // Done:
  size_t length;
  const string symbol = "\r\n\r\n";
  // initialize the buffer
  unsigned char buffer[1024] = {0xff};
  while ((length = buffer_.find(symbol)) == std::string::npos) {
    // use WrappedRead" to read data into the buffer_
    int res = WrappedRead(fd_, buffer, 1024);
    if (res == -1) {
      return false;
    } else if (res == 0) {
      break;
    } else {
      string tmp((const char*)buffer);
      buffer_ += tmp;
    }
  }
  if (length == string::npos) {
    return false;
  }
  // use ParseRequest() to parse the header into the *request argument.
  *request = ParseRequest(length + symbol.length());
  // preserve everything after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!
  buffer_ = buffer_.substr(length + symbol.length(), buffer_.size());
  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // Done:
  vector<string> lines;
  split(lines, str, is_any_of("\r\n"));
  trim(lines[0]);
  vector<string> first_line_words;
  // extract the RUI from the first line
  split(first_line_words, lines[0], is_any_of(" "));
  // check if it has valid format
  if (first_line_words.size() > 1 &&
      first_line_words[1].find("HTTP") == string::npos) {
    // if so, store it in req.URI
    req.URI = first_line_words[1];
  }
  // handle the additional lines
  for (auto it = lines.begin() + 1; it != lines.end(); it++) {
    string line = *it;
    trim(line);
    vector<string> pair;
    // check if it has valid format
    if (line.find(": ") != string::npos) {
      split(pair, line, is_any_of(": "), token_compress_on);
      string headername = pair[0];
      to_lower(headername);
      string headerval = pair[1];
      req.headers[headername] = headerval;
    }
  }

  return req;
}

}  // namespace hw4
