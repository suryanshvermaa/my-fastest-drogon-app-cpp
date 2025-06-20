/**
 *
 *  ErrorHandler.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class ErrorHandler : public HttpFilter<ErrorHandler>
{
  public:
    ErrorHandler() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

