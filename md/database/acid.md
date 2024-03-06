## Atomicity
The ability to abort a transaction on error and have all writes from that transaction discarded 

## Consistency
The application may have certain statements about data

## Isolation
concurrently executing transactions are isolated from each other

## Durability
once a transaction has committed successfully, any data it has written will not be forgotten, even if there is a
hardware fault or the database crashes.