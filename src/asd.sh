hlib=$HADOOP_HOME/share
export HADOOP_CLASSPATH=.
for f in $hlib/hadoop/common/hadoop-*.jar;
do
        HADOOP_CLASSPATH=${HADOOP_CLASSPATH}:$f
done
for f in $hlib/hadoop/common/lib/*.jar; 
do
      HADOOP_HOME  HADOOP_CLASSPATH=${HADOOP_CLASSPATH}:$f
done
for f in $hlib/hadoop/mapreduce/hadoop-*.jar;
do
        HADOOP_CLASSPATH=${HADOOP_CLASSPATH}:$f
done
for f in $hlib/hadoop/hdfs/hadoop-*.jar;
do
        HADOOP_CLASSPATH=${HADOOP_CLASSPATH}:$f
done
export CLASSPATH=.:$HADOOP_CLASSPATH:$CLASSPATH 