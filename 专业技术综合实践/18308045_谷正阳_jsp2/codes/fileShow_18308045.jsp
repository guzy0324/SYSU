<%@ page language = "java" import = "java.util.*" contentType = "text/html;charset=utf-8" %>
<!DOCTYPE HTML>
<html>
    <head>
        <title>实现文件上传</title>
    </head>
    <body>
        <form name = "fileUpload" action = "fileUpload_18308045.jsp" method = "POST" enctype="multipart/form-data">
            <p>id：<input type = text name = "id" size = 24></p>
            <p>文件名：<input type = file name = "file" size = 24></p>
            <p><input type = submit name = "submit" value = "OK"></p>
        </form>
    </body>
</html>
