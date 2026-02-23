{
  description = "Handmade Hero - Windows cross dev shell (clang)";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };

    llvm = pkgs.llvmPackages_latest;
    mingw = pkgs.pkgsCross.mingwW64;
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        # Clang compiler
        llvm.clang

        # Windows headers + libs
        mingw.windows.mingw_w64

        # LLD linker (faster, cleaner)
        llvm.lld

        # LSP + formatter
        pkgs.clang-tools

        # Build tools
        pkgs.cmake
        pkgs.gnumake

        # Optional: run .exe directly
        pkgs.wineWow64Packages.stable
      ];

      shellHook = ''
        echo "Windows cross dev shell ready (clang)."
        echo "Clang version: $(clang --version | head -n1)"
        echo "Target: x86_64-w64-windows-gnu"
      '';
    };
  };
}
