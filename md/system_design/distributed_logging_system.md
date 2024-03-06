Functional requirements:
    -

Non-functional requirements:
    - At least 20000 write requests per second
    - At least 20000 read requests per second for data that is less than 2 hour old
    - At least 10000 read requests per second for data that is less than 7 days old
    - Data should be available for at least 30 days
    - For each node, it at least should be able to store 10million of logs




## Metrics
 - FCP
  {
    name: "FCP",
    appId: "123",
    page: "/",
    seesionId: "123",
    url: "https://www.google.com",
    device: "chrome 90",
    os: "windows 10",
  }

  - Request INFO
  {
    name: "Request INFO",
    seesionId: "123",
    device: "chrome 90",
    os: "windows 10",
    url: "https://www.google.com",
  }

## Query


## Database

- TSDB
frontend metrics is naturally invariant to different clients, its not a time series data.
- NoSQL
- SQL
- Key-Value Store
- log structured data store