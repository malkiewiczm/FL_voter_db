-- post init to be run after importing the data
BEGIN TRANSACTION;
CREATE INDEX name_ordering ON voters(last_name, first_name);
COMMIT;
