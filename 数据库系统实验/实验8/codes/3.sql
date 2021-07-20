use school
set xact_abort on
begin transaction t3
    insert class values ('0001', '01CSC', 'CS')
    begin transaction t4
        insert class values ('0001', '01CSC', 'CS')
    commit transaction t4
commit transaction t3