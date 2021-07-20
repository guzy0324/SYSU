<%@ page language="java" import="java.util.*" 
         contentType="text/html; charset=utf-8"%>
<%
    request.setCharacterEncoding("utf-8");
    String name = "";
    String password = "";
    String campus = "";
    String grade = "";
    String clubs = "";
    String description = "";
    if (request.getParameter("save") != null)
    {
        name = request.getParameter("name");
        name =  name == null ? "*" : name + "*";
        password = request.getParameter("password");
        password = password == null ? "" : password;
        campus = request.getParameter("campus");
        campus = campus == null ? "" : campus;
        grade = request.getParameter("grade");
        grade = grade == null ? "" : grade;
        clubs = Arrays.toString(request.getParameterValues("club"));
        clubs = clubs == null ? "" : clubs;
        description = request.getParameter("description");
        description = description == null ? "*" : description + "*";
    }
    if (request.getParameter("exit") != null)
    {
        response.sendRedirect("http://172.18.187.6/");
    }
%>
<!DOCTYPE HTML>
<html>
  <head>
    <title>用户注册</title>
    <style> 
        textarea {
            vertical-align: top;
        }
    </style>
  </head>  
  <body>
    <form action="register3.jsp" method="post">
        <input type="hidden" name="id" value="12345">
        <p>同学名：<input type="text" name="name" value=<%=name%>></p>
        <p>密码：<input type="password" name="password" value=<%=password%>></p>
        <p>校区：
            南校区：<input type="radio" name="campus" value="south" <%=campus.equals("south")?"checked":""%>>
            东校区：<input type="radio" name="campus" value="east" <%=campus.equals("east")?"checked":""%>>
            北校区：<input type="radio" name="campus" value="north" <%=campus.equals("north")?"checked":""%>>
            珠海校区：<input type="radio" name="campus" value="zhuhai" <%=campus.equals("zhuhai")?"checked":""%>>
            深圳校区：<input type="radio" name="campus" value="shenzhen" <%=campus.equals("shenzhen")?"checked":""%>>
        </p>
        年级：<select type=text name="grade">
            <option value="freshman" <%=grade.equals("freshman")?"selected":""%>>大学一年级</option>
            <option value="sophomore" <%=grade.equals("sophomore")?"selected":""%>>大学二年级</option>
            <option value="junior" <%=grade.equals("junior")?"selected":""%>>大学三年级</option>
            <option value="senior" <%=grade.equals("senior")?"selected":""%>>大学四年级</option>
        </select>
        <p>社团：
        舞蹈队<input type="checkbox" name="club" value="dance" <%=clubs.indexOf("dance")>=0?"checked":""%>>
        摄影<input type="checkbox" name="club" value="photo" <%=clubs.indexOf("photo")>=0?"checked":""%>>
        篮球<input type="checkbox" name="club" value="basketball" <%=clubs.indexOf("basketball")>=0?"checked":""%>>
        </p>
        说明：<textarea name="description" rows="15" cols="40"><%=description%></textarea>
        <p>
            <input type=submit name="save" value="保存">
            <input type=submit name="exit" value="退出">
        </p>
    </form>
  </body>
</html>
