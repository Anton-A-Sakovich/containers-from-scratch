# export PS1='\e[0;32m\u@\h:\e[0m'
# cd Playground/ContainersFromScratch/ContainerProcess

mkdir /sys/fs/cgroup/systemd
mount -t cgroup -o none,name=systemd cgroup /sys/fs/cgroup/systemd

service docker start
