# Docker & Compose

You can run the backend in a container and the database in another container via docker-compose.

## Backend Image (Production)
- Multi-stage build in `Dockerfile` compiles the app and produces a minimal runtime image.

```bash
docker build -t drogon-app:latest -f Dockerfile .
docker run --rm -p 3001:3001 -e JWT_SECRET=your-secret-key drogon-app:latest
```

## Dev Image
- `Dockerfile.dev` provides a development toolchain and an entrypoint that builds and runs the app from a bind mount.

Typical usage (compose your own `docker run -v` dev flow), or integrate into `docker-compose.yml` as a service.

## Database via docker-compose
- `docker-compose.yml` defines a `postgres` service on `5432` and seeds schema from `init.sql`.

```bash
docker compose up -d postgres
```

Use `config.docker.json` as `config.json` inside the image so the app connects to `host: postgres` instead of `127.0.0.1`.
