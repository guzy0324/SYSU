use school
go
create rule r3 as @value > 50
go
exec sp_bindrule r3, 'worker.[sage]';