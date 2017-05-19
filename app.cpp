#include "includes/server.h"

server app;

bool checkLogin();
bool safe_check(string input);
string index();
string login();
string regist();
string profile();
string ranklist();

int main()
{
    
    app._route.bind_path(string("/"), index);
    app._route.bind_path(string("/index"), index);
    app._route.bind_path(string("/login"), login);
    app._route.bind_path(string("/regist"), regist);
    app._route.bind_path(string("/profile"), profile);
    app._route.bind_path(string("/rank"), ranklist);
    app.Listen();
    return 0;
}


bool checkLogin()
{
    if (!app._COOKIE.empty() && app._COOKIE.find(string("sessionid"))!=app._COOKIE.end())
    {
        if (app.session_schedule.find(app._COOKIE[string("sessionid")]))
        {
            app._SESSION.load(app._COOKIE[string("sessionid")]);
            cout<<app._SESSION[string("test")];
            return true;
        }
    }
    return false;
}

bool safe_check(string input)
{
    string tmp = input;
    toLowerString(tmp);
    if(tmp.find("select")!=-1 || tmp.find("union")!=-1)
        return false;
    return true;
}

string index()
{
    map<string,string> none;
    if(!checkLogin())
    {
        none[string("message")] = "You need to login!";
        render newrender;
        return newrender.render_from_template(string("login.html"), none);
    }
    render newrender;
    return newrender.render_from_template(string("index.html"), none);
}


string login()
{    
    if(checkLogin())
    {
        render newrender;
        map<string, string> none;
        return newrender.render_from_template(string("index.html"), none);// TODO state 302 is standard
    }
    if (!app._POST.empty() && app._POST.find(string("username")) != app._POST.end() && app._POST.find(string("password"))!= app._POST.end())
    {
         
         string username = app._POST[string("username")];
         string password = app._POST[string("password")];
         if (safe_check(username) && safe_check(password))
         {
             imysql newcon;
             newcon.init();
             string sql;
             sql = "select id, email from oj_stu_users where username=\"" + username + "\" and password =\"" + password +"\";";
             newcon.execute(sql);
             if (newcon.count_rows()>0)
             {
                 MYSQL_ROW row = newcon.get_next_row();
                 string id = row[0];
                 string email = row[1];
                 string session_id = app._SESSION.newSession();
	         app._SESSION[string("id")] = id;
                 app._SESSION[string("username")] = username;
                 app._SESSION[string("email")] = email;
	         app._SESSION.save(session_id, app.session_schedule);
                 app.set_cookie(string("sessionid"), session_id);
                 render newrender;
                 map<string,string> none;
                 return newrender.render_from_template(string("index.html"), none);
             }
         }
         map<string, string> fail;
         fail[string("message")] = "The username or password is wrong!";
         render newrender;
         return newrender.render_from_template(string("login.html"), fail);
    }
    map<string, string> pro;
    pro[string("message")] = "You need to login!";
    render newrender;
    return newrender.render_from_template(string("login.html"), pro);
}


string regist()
{
    if (!app._POST.empty() && app._POST.find(string("username")) != app._POST.end() && app._POST.find(string("password"))!= app._POST.end() && app._POST.find(string("email"))!= app._POST.end() && app._POST.find(string("confirm"))!= app._POST.end())
    {
        string username = app._POST[string("username")];
        string password = app._POST[string("password")];
        string confirm = app._POST[string("confirm")];
        
        if (password != confirm)
        {
            map<string, string> fail;
            fail[string("message")] = "<p>The two passwords are not consistent!</p>";
            render newrender;
            return newrender.render_from_template(string("regist.html"), fail);
        }
        string email = urlDecode(app._POST[string("email")]);
        cout<<confirm<<"!!!!!";
        // TODO username, password, email format check
        if (safe_check(username) && safe_check(password) && safe_check(email))
        {
            imysql newcon;
            newcon.init(); 
            string sql = "insert into oj_stu_users(username, password, email) values('"+username+"','"+password+"','" + email+"');";
            newcon.execute(sql);
            sql = "select id from oj_stu_users where username=\"" + username + "\";";
            newcon.execute(sql);
            if (newcon.count_rows()>0)
            {
                MYSQL_ROW row = newcon.get_next_row();
                string id = row[0];
                sql = "insert into oj_stu_solved(id, solved, score) values(" + id + ",'',0);";
                newcon.execute(sql);
                map<string, string> success;
                success[string("message")] = "Register success!";
                render newrender;
                return newrender.render_from_template(string("login.html"), success);
            }
        }
    }
    map<string, string> none;
    none[string("message")] = "";
    render newrender;
    return newrender.render_from_template(string("regist.html"), none);
}

string profile()
{
    map<string,string> info;
    if(!checkLogin())
    {
        info[string("message")] = "You need to login!";
        render newrender;
        return newrender.render_from_template(string("login.html"), info);
    }
    info[string("name")] = app._SESSION[string("username")];
    info[string("email")] = app._SESSION[string("email")];
    render newrender;
    return newrender.render_from_template(string("profile.html"), info); 
}


string ranklist()
{
    map<string,string> none;
    if(!checkLogin())
    {
        none[string("message")] = "You need to login!";
        render newrender;
        return newrender.render_from_template(string("login.html"), none);
    }
    imysql newcon;
    string ranklist = "";
    newcon.init();
    string sql = "select oj_stu_users.username, oj_stu_solved.solved, oj_stu_solved.score from oj_stu_users join oj_stu_solved on oj_stu_users.id = oj_stu_solved.id;";
    newcon.execute(sql);
    if(newcon.count_rows() > 0)
    {
        MYSQL_ROW row;    
        int count = 1;
        while(row = newcon.get_next_row())
        {
            string username = row[0]; 
            string solved = row[1];  
            string score = row[2];
            ranklist += "<tr><td scope=\"row\">"+to_String(count)+"</td>";
	    ranklist += "<td><a href=\"/profile?name=\""+username+"\">"+username+"</a></td>";
	    ranklist += "<td>" + score +"pt</td></tr>";
            count++;
        }
    }
    map<string,string> info;
    info[string("users")] = ranklist;
    render newrender;
    return newrender.render_from_template(string("profile.html"), info); 
}
