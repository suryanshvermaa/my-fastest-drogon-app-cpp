export interface Todo {
  id: number
  title: string
  completed: boolean
}

export type FilterType = "all" | "active" | "completed"

export interface AIMessage {
  role: "user" | "assistant"
  content: string
  timestamp: Date
}
