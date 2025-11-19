# Database & ORM

The project uses PostgreSQL 15. Schema is defined in `init.sql` and ORM models are generated with `drogon_ctl`.

## Schema
```sql
CREATE TABLE users (
  id SERIAL PRIMARY KEY,
  name VARCHAR(255) NOT NULL,
  email VARCHAR(255) UNIQUE NOT NULL,
  password VARCHAR(255) NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE todos (
  id SERIAL PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  title VARCHAR(255) NOT NULL,
  completed BOOLEAN DEFAULT FALSE,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

## ORM Models
Generated classes live under `src/models/` (e.g., `Users`, `Todos`). Use `drogon::orm::Mapper<T>` to query and mutate records.

Example insertion (simplified):

```cpp
Mapper<Todos> mapper(app().getDbClient());
Todos t; t.setTitle("Buy milk"); t.setUserId(1); t.setCompleted(false);
mapper.insert(t, /* onSuccess */ [](const Todos &row){ /* ... */ }, /* onError */ ...);
```

## (Re)Generating Models
If you change the database schema, update `src/models/model.json` and regenerate models:

```bash
drogon_ctl create model src/models/model.json
```

Make sure new source files are compiled by CMake if paths change.
