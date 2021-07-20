begin tran t1
    update teachers
    set salary = 0
    where tid = '200003125'
    save tran t2
    insert into courses
    values ('10001', 'gg', 0)
    if @@ERROR != 0
        begin
            rollback tran t2
            print 'hahahahah'
            return
        end
commit tran t1
