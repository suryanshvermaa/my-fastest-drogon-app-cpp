"use client"

import { TodoApp } from "@/components/TodoApp"
import { useRouter } from "next/navigation"
import { useEffect } from "react"

export default function Page() {
  const router=useRouter();
  useEffect(()=>{
    const token=localStorage.getItem("token");
    if(!token) router.push("/auth/login-signup")
  },[])
  return <TodoApp />
}
