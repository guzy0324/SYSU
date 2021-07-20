create trigger tri on v
instead of insert
as
begin
    set nocount on
    if
    (
        not exists
        (select s.sid from students s, inserted i
        where s.sid = i.sid)
    )
    begin
        insert into students
            select sid, sname, null, null from inserted
        insert into stu_card
            select card_id, sid, null from inserted
    end
end