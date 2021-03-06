--
-- PLTSQL -- Local Temporary Objects
--

CREATE FUNCTION create_local_temp_table() RETURNS void AS $$
    DECLARE @val int;
BEGIN
    CREATE TABLE #test (a int);

    -- Check the schema the table was created under
    PERFORM nspname
    FROM    pg_namespace
    WHERE   oid = (SELECT relnamespace FROM pg_class WHERE relname = '#test')
    AND     nspname LIKE 'pg_temp_%';

    IF FOUND
        PRINT 'Local temporary table created.';

    -- Perform some basic DML operations on the temporary table
    INSERT INTO #test VALUES (1);
    SELECT a INTO @val FROM #test;
    PRINT @val;

    -- Perform some basic normal table creation sanity tests
    CREATE TEMPORARY TABLE test (a int);
    CREATE TABLE test2 (a int, b text);
END
$$ LANGUAGE pltsql;

SELECT create_local_temp_table();

DROP TABLE test;
DROP TABLE test2;

CREATE FUNCTION create_local_temp_table_dynamically() RETURNS void AS $$
    DECLARE @stmt text = 'CREATE TABLE #test2 (a int, b int)',
            @val int;
BEGIN
    EXECUTE @stmt;      -- CREATE TABLE -> CREATE TEMPORARY TABLE transformation
    EXECUTE 'INSERT INTO #test2 VALUES (1, 2)'; -- Ident quoting in other contexts

    IF EXISTS (SELECT b FROM #test2)
        PRINT 'Success'

    EXECUTE 'SELECT a FROM #test2' INTO @val;
    PRINT @val;

    -- Perform some basic normal table creation sanity tests
    EXECUTE 'CREATE TEMPORARY TABLE test (a int)';
    EXECUTE 'CREATE TABLE test2 (a int, b text)';
END
$$ LANGUAGE pltsql;

SELECT create_local_temp_table_dynamically();

DROP TABLE test;
DROP TABLE test2;

CREATE FUNCTION access_temp_table_from_another_proc() RETURNS int AS $$
    DECLARE @val int;
BEGIN
    SELECT b INTO @val FROM #test2;
    RETURN @val;
END
$$ LANGUAGE pltsql;

SELECT access_temp_table_from_another_proc();

-- Test from outside PL/TSQL as a quoted table
SELECT a, b FROM "#test2";

CREATE FUNCTION nest_function_with_temp_tables() RETURNS void AS $$
BEGIN
    CREATE OR REPLACE FUNCTION nested() RETURNS void AS '
        BEGIN
            CREATE TABLE #test3 (a int);
            EXECUTE ''CREATE TABLE #test4 (a int)'';
        END
    ' LANGUAGE pltsql;
END
$$ LANGUAGE pltsql;

SELECT nest_function_with_temp_tables();
SELECT nested();

SELECT COUNT(relname) FROM pg_class WHERE relname IN ('#test3', '#test4');
