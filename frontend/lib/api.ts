async function fetchJSON<T = unknown>(path: string, init?: RequestInit): Promise<T> {
  const tryFetch = async (base: string) => {
    const res = await fetch(`${base}${path}`, { credentials: "include", ...init })
    if (!res.ok) throw new Error(`HTTP ${res.status} ${res.statusText}`)
    const type = res.headers.get("content-type") ?? ""
    if (!type.includes("application/json")) throw new Error("not-json")
    return res.json() as Promise<T>
  }

  const BASE_CANDIDATES: string[] = [
    // 1) .env override
    (import.meta as any).env?.VITE_API_URL?.replace(/\/$/, ""),
    // 2) common local-dev default
    `${process.env.NEXT_BACKEND_URL}/api`,
    // 3) same origin (preview proxy)
    `${window.location.origin}/api`,
  ].filter(Boolean)

  const bases = _resolvedBase ? [_resolvedBase] : BASE_CANDIDATES
  const errors: string[] = []

  for (const base of bases) {
    try {
      const data = await tryFetch(base)
      _resolvedBase = base // remember successful base
      return data
    } catch (err: any) {
      errors.push(`${base}: ${err.message}`)
    }
  }

  throw new Error(`Could not reach API.\n${errors.join("\n")}`)
}

let _resolvedBase: string | null = null

export const todoApi = {
  list: () => fetchJSON<Array<{ id: number; title: string; completed: boolean }>>("/todos"),

  create: (title: string) =>
    fetchJSON<{ id: number; title: string; completed: boolean }>("/todos", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ title, completed: false }),
    }),

  update: (id: number, updates: Partial<{ title: string; completed: boolean }>) =>
    fetchJSON<{ id: number; title: string; completed: boolean }>(`/todos/${id}`, {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(updates),
    }),

  remove: (id: number) =>
    fetchJSON<void>(`/todos/${id}`, {
      method: "DELETE",
    }),
}
