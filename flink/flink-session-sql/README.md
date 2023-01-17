# Flink SQL Client with Session Cluster

Reference: [Apache Flink Docker Setup](https://nightlies.apache.org/flink/flink-docs-release-1.16/docs/deployment/resource-providers/standalone/docker/)

## Manual Setup

```bash
FLINK_PROPERTIES="jobmanager.rpc.address: jobmanager"
docker network create flink-network

# Launch the JobManager
docker run \
    --rm \
    --name=jobmanager \
    --network flink-network \
    --publish 8081:8081 \
    --env FLINK_PROPERTIES="${FLINK_PROPERTIES}" \
    flink:1.16.0-scala_2.12-java11 jobmanager

# Launch one or more TaskManager containers
docker run \
    --rm \
    --name=taskmanager \
    --network flink-network \
    --env FLINK_PROPERTIES="${FLINK_PROPERTIES}" \
    flink:1.16.0-scala_2.12-java11 taskmanager
# Web interface: http://localhost:8081

# Submission of a job
./bin/flink run ./examples/streaming/TopSpeedWindowing.jar
```

## Flink with Docker Compose

```bash
# Launch a cluster
docker-compose up
# Web interface: http://localhost:8081

# Scale the cluster up or down
docker-compose scale taskmanager=<N>

# Access the JobManager container
docker exec -it $(docker ps --filter name=jobmanager --format={{.ID}}) /bin/bash
# Access the TaskManager container
docker exec -it $(docker ps --filter name=taskmanager --format={{.ID}}) /bin/bash
# NOTE: the execution log will be stored on the task manager

# Start the SQL client
docker-compose run sql-client

# Kill everything
docker-compose down
```
