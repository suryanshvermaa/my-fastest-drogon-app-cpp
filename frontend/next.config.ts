import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  reactStrictMode: false,
  eslint:{
    ignoreDuringBuilds:false
  }
};

export default nextConfig;
