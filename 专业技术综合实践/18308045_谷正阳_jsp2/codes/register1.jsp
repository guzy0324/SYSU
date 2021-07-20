<%@ page language="java" import="java.util.*" 
         contentType="text/html; charset=utf-8"%>
<%request.setCharacterEncoding("utf-8");%>
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
    <form action="register2.jsp" method="post">
        <input type="hidden" name="id" value="12345">
        <p>同学名：<input type="text" name="name"></p>
        <p>密码：<input type="password" name="password"></p>
        <p>校区：
            南校区：<input type="radio" name="campus" value="south">
            东校区：<input type="radio" name="campus" value="east">
            北校区：<input type="radio" name="campus" value="north">
            珠海校区：<input type="radio" name="campus" value="zhuhai">
            深圳校区：<input type="radio" name="campus" value="shenzhen">
        </p>
        年级：<select type=text name="grade">
            <option value="freshman">大学一年级</option>
            <option value="sophomore">大学二年级</option>
            <option value="junior">大学三年级</option>
            <option value="senior">大学四年级</option>
        </select>
        <p>社团：
            舞蹈队<input type="checkbox" name="club" value="dance">
            摄影<input type="checkbox" name="club" value="photo">
            篮球<input type="checkbox" name="club" value="basketball">
        </p>
        说明：<textarea name="description" rows="15" cols="40"></textarea>
        <p>
            <input type=submit name="save" value="保存">
            <input type=submit name="exit" value="退出">
        </p>
    </form>
  </body>
</html>
