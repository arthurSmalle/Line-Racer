{
  description = "nieuwste python met juiste libs";
  inputs = 
  {
      nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };
  outputs = { self, nixpkgs, ... }@inputs:
    let
    pkgs = import nixpkgs { system = "x86_64-linux"; config.allowUnfree = true;};
    in
    {
      devShells.x86_64-linux.default =
      pkgs.mkShell
      {
        nativeBuildInputs = with pkgs; [
          cowsay #voor funny redenen
	  python3
	  uv
	  python313Packages.numpy
	  python313Packages.matplotlib
	  python313Packages.pillow
	  python313Packages.bleak
	  python313Packages.tkinter
        ];
    
    shellHook = ''
    export SHELL=/run/current-system/sw/bin/bash
    cowsay -b "welcom to pycharm shell"
#   pycharm-community
    '';
      };
    };
  }
