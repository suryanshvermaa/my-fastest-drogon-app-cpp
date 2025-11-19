# Troubleshooting

## Build Issues
- Ensure Drogon is installed (`ldconfig` run) and `find_package(Drogon REQUIRED)` succeeds.
- Check compiler supports C++20: `g++ --version`.
- Clean build: `rm -rf build && mkdir build && cd build && cmake .. && cmake --build . -j`.

## Database
- Verify DB is running and reachable: `psql -h 127.0.0.1 -U postgres -d userdb`.
- If using compose: `docker compose logs postgres`.

## JWT
- Ensure `JWT_SECRET` is exported or set in the container.
- Invalid/expired token -> 401 from `auth` filter.

## Ports and CORS
- Backend listens on `3001` per `config.json`.
- If CORS issues persist, confirm requests include correct `Origin` and that responses include `Access-Control-Allow-Origin`.

## Docker
- Reset DB volume (DANGEROUS – data loss): `docker compose down -v && docker compose up -d postgres`.
- Rebuild image after code changes: `docker build --no-cache -t drogon-app:latest -f Dockerfile .`.
