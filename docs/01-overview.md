# Overview

This project demonstrates a high-performance REST API using the Drogon C++ framework, backed by PostgreSQL for persistence and paired with a modern Next.js frontend.

## What You’ll Learn
- How a Drogon application is bootstrapped (`src/main.cc`)
- How to define controllers, routes, and filters (middleware)
- How to use Drogon ORM for models
- How JWT auth is implemented end-to-end
- How to run locally and in Docker

## Architecture

```
┌─────────────┐         ┌──────────────┐         ┌──────────────┐
│   Next.js   │────────▶│  Drogon C++  │────────▶│  PostgreSQL  │
│  Frontend   │  HTTP   │   Backend    │   ORM   │   Database   │
│  (Port 3000)│         │  (Port 3001) │         │  (Port 5432) │
└─────────────┘         └──────────────┘         └──────────────┘
```

- CORS is handled globally in `src/main.cc` and a dedicated `CorsMiddleware` (not required for basic usage).
- JWT is validated in `src/filters/auth.*`; validated user info is injected as request parameters.
- Controllers live under `src/controllers/` and expose scoped routes under `/api/v1/...`.

## Tech
- Drogon v1.9.0, C++20, CMake
- PostgreSQL 15
- JWT-CPP for tokens, Bcrypt for password hashing
- Docker and Docker Compose for containerization
