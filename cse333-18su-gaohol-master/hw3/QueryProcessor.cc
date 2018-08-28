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

#include <iostream>
#include <algorithm>

#include "./QueryProcessor.h"

extern "C" {
  #include "./libhw1/CSE333.h"
}

namespace hw3 {

static list<docid_element_header> Insert
(const list<docid_element_header> l1, const list<docid_element_header> l2);
static int Attach
(const list<docid_element_header> list, DocTableReader* docReader,
       vector<QueryProcessor::QueryResult>* finalresult);
QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (HWSize_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (HWSize_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Verify333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // Done:
  for (HWSize_t i = 0; i < arraylen_; i++) {
    IndexTableReader* idxReader = itr_array_[i];
    DocTableReader* docReader = dtr_array_[i];
    // lookup the first word in query
    DocIDTableReader* didt_0 = idxReader->LookupWord(query[0]);
    // if not found
    if (didt_0 == nullptr) {
      delete(didt_0);  // free the current docIDTableReader
      continue;
    }
    // get the docidlist for corresponding to first word of query
    auto result_0 = didt_0->GetDocIDList();
    // lookup the other words in query and find corresponding docidlist
    for (HWSize_t i = 1; i < query.size(); i++) {
      DocIDTableReader* didt_i = idxReader->LookupWord(query[i]);
      if (didt_i == nullptr) {
        result_0.clear();
        delete(didt_i);
        break;
      }
      // get te docidlist
      auto result_i = didt_i->GetDocIDList();
      // combine docidlist of first word and current word
      result_0 = Insert(result_0, result_i);
      delete(didt_i);
    }
    // find the info of all related files
    int op = Attach(result_0, docReader, &finalresult);
    // check if it is empty
    if (op == 0) {
      delete(didt_0);
      continue;
    }
    delete(didt_0);
  }
  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

static int Attach
(const list<docid_element_header> list, DocTableReader* docReader,
       vector<QueryProcessor::QueryResult>* finalresult) {
  // check if no results
  if (list.size() == 0) {
    return 0;
  }
  // get all of matched files' info
  for (auto& elh : list) {
    // docid
    DocID_t docid = elh.docid;
    // num positions
    HWSize_t num_positions = elh.num_positions;
    QueryProcessor::QueryResult qres;
    Verify333(docReader->LookupDocID(docid, &qres.document_name));
    // get rank
    qres.rank = num_positions;
    // attach to the finalresult
    (*finalresult).push_back(qres);
  }
  return 1;
}

static list<docid_element_header> Insert
(const list<docid_element_header> l0, const list<docid_element_header> l1) {
  list<docid_element_header> result;
  // iterate all the element headers in docidlist
  // related to first word in query
  for (auto& deh0 : l0) {
    HWSize_t num_positions = deh0.num_positions;
    // iterate all the element headers in docidlist
    // related to current word in query
    for (auto& deh1 : l1) {
      // if their docid matched
      if (deh1.docid == deh0.docid) {
        // update the num_positions
        num_positions += deh1.num_positions;
        // write the header
        docid_element_header header = {deh1.docid, num_positions};
        // combine two docidlist
        result.push_back(header);
        break;
      }
    }
  }
  return result;
}

}  // namespace hw3
