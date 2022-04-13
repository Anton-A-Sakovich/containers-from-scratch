dotnet build -v q

docker create --name temp mcr.microsoft.com/dotnet/runtime:6.0 dotnet /root/app/ContainerProcess.dll
docker cp bin/Debug/net6.0/ temp:/root/app
docker start temp

sleep 4
echo "===================== ps -A f as seen from host process: ====================="
dotnet bin/Debug/net6.0/ContainerProcess.dll

sleep 2
echo "===================== ps -A f as seen from container process: ====================="
docker logs temp

docker container rm temp

# ./run.sh
