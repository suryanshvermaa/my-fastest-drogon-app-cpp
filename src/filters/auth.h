/**
 *
 *  auth.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class auth : public HttpFilter<auth>
{
  public:
    auth() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

