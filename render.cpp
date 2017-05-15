#include "includes/render.h"

render::render()
{
    temp_pattern[string("variable")] = "{\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*}";
    
}

render::~render()
{}


string &render::render_from_string(string &content, map<string, string> param)
{
    smatch result;
    regex replace, search_pattern;
    string::const_iterator start = content.begin();
    string::const_iterator end = content.end();
    search_pattern.assign(temp_pattern[string("variable")]);

    // replace variable with { varibale_name }
    while ( regex_search(start, end, result, search_pattern))
    {    
        start = result[0].second;
        if(param.count(result[1].str())>0)
        {
            string pattern("{\\s*");
            pattern += (result[1].str() + "\\s*}");
            replace.assign(pattern);
	    replace_all_regex(content, replace, param[result[1].str()]);
	}
    }
    return content;
}


string render::render_from_template(string temp_name, map<string, string> param)
{
    ifstream infile;
    infile.open(string(TEMPLATE_PATH) + temp_name);
    if (!infile)
    {
        // file open error
    }
    std::stringstream buffer;  
    buffer << infile.rdbuf();  
    std::string content(buffer.str());  
    infile.close();
    return render_from_string(content, param);
}
