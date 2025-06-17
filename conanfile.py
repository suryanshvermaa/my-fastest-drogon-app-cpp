from conan import ConanFile

class MyDrogonAppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("drogon/1.9.10")