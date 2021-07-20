use school
go
create trigger T6 on worker
for update
as
if (select number from updated) = '00001'
begin
print 'Transaction fail'
rollback transaction
end
