/**
 *
 *  CorsMiddleware.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class CorsMiddleware : public HttpFilter<CorsMiddleware>
{
  public:
    CorsMiddleware() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

