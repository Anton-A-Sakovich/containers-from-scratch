rm -r /root/bin/
cp -r bin/ /root/bin/

docker run --detach --name temp container-process:latest dotnet /root/bin/ContainerProcess.dll

echo "================================"
echo "Host processes:"
dotnet /root/bin/ContainerProcess.dll
echo "================================"

echo "================================"
echo "Container processes:"
docker logs temp
echo "================================"

docker container rm temp