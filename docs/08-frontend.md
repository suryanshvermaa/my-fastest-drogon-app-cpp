# Frontend Quickstart (Next.js)

A Next.js 15 frontend is included under `frontend/`. It communicates with the backend at `http://localhost:3001/api/v1`.

## Run
```bash
cd frontend
npm install
npm run dev
# open http://localhost:3000
```

## Integration Notes
- CORS is already enabled in the backend.
- Set the API base URL in your frontend utilities (see `frontend/lib/api.ts`) to `http://localhost:3001/api/v1` if not already.
- Include `Authorization: Bearer <jwt>` after logging in.
