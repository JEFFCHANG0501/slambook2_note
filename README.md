# slambook2

## Build Dev Environment
```bash
docker compose -f docker-compose.yaml up slambook2-dev -d
```

## Enter Dev Container
1. vscode (ctrl+shift + p)
2. Dev Containers: Attach to Running Containers ...
3. Choose /slambook2-dev

## Build 3rdparty dependency
```bash
# install Sophus
cd /workspaces/3rdparty/Sophus/
mkdir build
cmake ..
make -j $(nproc)
make install

# install Pangolin
cd /workspaces/3rdparty/Pangolin
mkdir build
cmake ..
make -j $(nproc)
make install
```