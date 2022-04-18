rm -r /root/bin/
cp -r bin/ /root/bin/

CONTAINER_ID=`docker container ls --quiet --filter 'name=temp'`
if [ -z CONTAINER_ID ]
then
    docker container rm --force temp
fi

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