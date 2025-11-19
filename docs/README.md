# Drogon C++ Todo App — Documentation

This documentation walks you through setting up, understanding, and extending a production-ready Drogon (C++) + PostgreSQL backend with a Next.js frontend. It uses this repository as a complete, working example.

- Start here if you’re new to Drogon, then follow the sections below.

## Contents
- [Overview](./01-overview.md)
- [Setup (Linux) and Running](./02-setup.md)
- [Backend Architecture](./03-backend.md)
- [API Reference](./04-api.md)
- [Auth & Security](./05-auth.md)
- [Database & ORM](./06-database.md)
- [Docker & Compose](./07-docker.md)
- [Frontend Quickstart](./08-frontend.md)
- [Troubleshooting](./09-troubleshooting.md)

## Quick Links
- Backend entrypoint: `src/main.cc`
- Controllers: `src/controllers/`
- Filters (JWT): `src/filters/`
- Models (ORM): `src/models/`
- Utilities (JWT, errors): `src/utils/`
- Config: `config.json`, `config.docker.json`
- Build config: `CMakeLists.txt`

> Tip: If you’re only trying the API quickly, skip to [Docker & Compose](./07-docker.md).