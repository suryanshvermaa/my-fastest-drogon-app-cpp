# Auth & Security

JWT-based authentication protects user-specific routes. Passwords are stored hashed using Bcrypt.

## Token
- Created in `src/utils/token.cc` using `jwt-cpp` with HS256.
- Claims: `userId` (string), `email` (string)
- Issuer: `suryansh`, Type: `JWS`, Expiry: 24h
- Secret: `JWT_SECRET` (environment variable) — required at runtime.

## Filter: `auth`
The `auth` filter validates `Authorization: Bearer <token>` and injects into request parameters:
- `userId` — numeric user ID
- `email` — user email

If validation fails, the filter returns 401 with a JSON error and the handler is not called.

## Controller Protection
Routes that require authentication include the filter name `"auth"` in their method declarations, e.g.:

```cpp
METHOD_ADD(User::profile, "/profile", Get, "auth");
```

## CORS
CORS is handled via:
- Pre-routing advice for OPTIONS preflight requests
- Post-handling advice adding `Access-Control-Allow-Origin: *`
- Optional `CorsMiddleware` is included but not strictly necessary given the global advices.
