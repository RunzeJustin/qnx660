# This script is sets environment variables requires to use this version of QNX Software Development Platform 6.6
# from the command line. To use the script, you have to "source" it into your shell,
# source qnx660-env.sh
# if source command is not available use "." (dot) command instead
#
QNX_TARGET=/opt/qnx660/target/qnx6
QNX_HOST=/opt/qnx660/host/linux/x86
QNX_CONFIGURATION=/opt/qnx660/.qnx
MAKEFLAGS=-I/opt/qnx660/target/qnx6/usr/include
PATH=/opt/qnx660/host/linux/x86/usr/bin:/opt/qnx660/.qnx/bin:/opt/qnx660/jre/bin:$PATH

export QNX_TARGET QNX_HOST QNX_CONFIGURATION MAKEFLAGS PATH
unset PYTHONPATH

# Include CAR2.1 Environments if present
qnxCarDeployment=/opt/qnx660/deployment/qnx-car
[ -x $qnxCarDeployment/qnxcar-env.sh ] && 
   . $qnxCarDeployment/qnxcar-env.sh
