Read Committed
1. When reading from database, the transaction will only read the committed data.
2. When writing to database, the transaction will only write to the committed data.

Implementation
For every object that is written, the database remembers both the old committed value and the new value set by the transaction that currently holds the write lock. While the transaction is ongoing, any other transaction that read the object are simply given the old value.

Issue
Inconsistencies value bettwen old committed value and other committed value, eg: account A transfer 100 to account B,
when read, the account A may has (amountA - 100) but account B still only has (amountB). And some situations cannot tolerate such temporary inconsistency: Backup(the inconsistency may become permanent), Analytics, etc.