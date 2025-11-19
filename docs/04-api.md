# API Reference

Base URL: `http://localhost:3001/api/v1`

All `todos` endpoints require `Authorization: Bearer <token>` header. Authentication endpoints return a JWT for subsequent calls.

Note: In success responses for `signup` and `login`, the field is spelled `sucess` (typo in code). Error responses use `success: false`.

## Health
- GET `/health/`
  - 200: `{ "success": true, "message": "healthy" }`

## Auth

### Signup
- POST `/User/signup`
- Body (JSON):
  ```json
  { "name": "Alice", "email": "alice@example.com", "password": "secret" }
  ```
- 201:
  ```json
  {
    "sucess": true,
    "message": "signup successful",
    "data": { "id": 1, "name": "Alice", "email": "alice@example.com", "token": "<jwt>" }
  }
  ```

### Login
- POST `/User/login`
- Body (JSON):
  ```json
  { "email": "alice@example.com", "password": "secret" }
  ```
- 200:
  ```json
  {
    "sucess": true,
    "message": "login successful",
    "data": { "id": 1, "name": "Alice", "email": "alice@example.com", "token": "<jwt>" }
  }
  ```

### Profile
- GET `/User/profile`
- Headers: `Authorization: Bearer <jwt>`
- 200:
  ```json
  { "success": true, "message": "profile fetched successfully", "data": { "userId": "1" } }
  ```

## Todos
Controller class is `api::v1::todos`. Some routes are absolute (prefixed fully) and some relative to `/api/v1/todos`.

### Create Todo
- POST `/todos/create`
- Headers: `Authorization: Bearer <jwt>`
- Body (JSON):
  ```json
  { "title": "Buy milk", "completed": false }
  ```
- 201:
  ```json
  {
    "success": true,
    "message": "created todo",
    "data": { "id": 10, "title": "Buy milk", "completed": false }
  }
  ```

### Get All Todos (for current user)
- GET `/todos/getAll`
- Headers: `Authorization: Bearer <jwt>`
- 200:
  ```json
  { "success": true, "message": "fetched", "data": [ {"id":1,"title":"...","completed":false} ] }
  ```

### Get Todos by Completion
- GET `/todos/getAll/{completion}` (absolute path is `/api/v1/todos/getAll/{completion}`)
- Path params: `completion` is `true` or `false`
- Headers: `Authorization: Bearer <jwt>`

### Get Single Todo
- GET `/todos/{id}` (absolute path `/api/v1/todos/{id}`)
- Headers: `Authorization: Bearer <jwt>`

### Update Todo
- PUT `/todos/update/{id}` (absolute path `/api/v1/todos/update/{id}`)
- Headers: `Authorization: Bearer <jwt>`
- Body (JSON):
  ```json
  { "title": "New title", "completed": true }
  ```

### Delete Todo
- DELETE `/todos/delete/{id}` (absolute path `/api/v1/todos/delete/{id}`)
- Headers: `Authorization: Bearer <jwt>`

## Error Model
Errors generally return:
```json
{ "success": false, "message": "..." }
```

## Postman
A Postman collection with environment is expected under `docs/postman/` (if provided). Import it and set the `base_url` variable to `http://localhost:3001/api/v1` and `jwt` after login.
