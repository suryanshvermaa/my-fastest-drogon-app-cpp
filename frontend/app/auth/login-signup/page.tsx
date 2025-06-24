"use client"

import { useState } from "react"
import LoginForm from "../../../components/LoginPage"
import SignupForm from "../../../components/SignUpPage"
import { Button } from "../../../components/ui/Button"

export default function Home() {
  const [isLogin, setIsLogin] = useState(true)

  return (
    <main className="flex min-h-screen flex-col items-center justify-center p-4 bg-gray-50">
      <div className="w-full max-w-md">
        <div className="flex justify-center mb-6">
          <div className="flex bg-muted rounded-lg p-1">
            <Button
              variant={isLogin ? "primary" : "ghost"}
              size="sm"
              onClick={() => setIsLogin(true)}
              className="rounded-md"
            >
              Login
            </Button>
            <Button
              variant={!isLogin ? "primary" : "ghost"}
              size="sm"
              onClick={() => setIsLogin(false)}
              className="rounded-md"
            >
              Sign Up
            </Button>
          </div>
        </div>
        {isLogin ? <LoginForm /> : <SignupForm />}
      </div>
    </main>
  )
}
