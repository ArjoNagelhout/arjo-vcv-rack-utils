# Arjo VCV-Rack-Utils

I needed a certain module, so I made it. 

Docs for creating plugins: https://vcvrack.com/manual/Building and https://vcvrack.com/manual/PluginDevelopmentTutorial

Build (works on my machine ;)):

```shell
brew install jq
export RACK_DIR=~/Documents/Rack-SDK
cd ~/Documents/Experiments/arjo-vcv-rack-utils
make
make dist
cp -R dist/arjo-vcv-rack-utils ~/Documents/Rack2/plugins-mac-arm64
```
