#include "includes/session.h"

session::session()
{
	cache.clear();
        no_element = "No such key";
}

string session::serialize(mss &session_map)
{
	// self-desingned serialize...
	string content = "";
	for(mss::iterator itr=session_map.begin();   itr!=session_map.end(); ++itr)
	{
		content += "{\"" + itr->first + "\":\"" + itr->second + "\"}";   //incovinient!!!!
	} 
	return content;
}

mss session::unserialize(string &content)
{
    Trim(content);
    regex para_pattern("{\"([A-Za-z0-9_]+)\":\"([A-Za-z0-9_%@\\.\\+\\-]+)\"}");
    smatch result;
    mss para;

    string::const_iterator start = content.begin();
    string::const_iterator end = content.end();
	
    while ( regex_search(start, end, result, para_pattern))
    {
        para[result[1].str()] = result[2].str();
        start = result[0].second;
    }

    return para;
}

void session::load(string session_id)
{
	ifstream session_in;
        session_in.open(session_id.c_str());
	string content;
	session_in>>content;
	cache = unserialize(content);
}


void session::save(string session_id, heap<string> &schedule, int expire_time)
{
	ofstream outfile;
        outfile.open(session_id.c_str());
	string content = serialize(cache);
	outfile<<content;
	outfile.close();
        
	int expired_time = time(NULL) + expire_time;
	
	for (int i = 0; i < schedule.size(); i++)
	{
            if (schedule.data[i].value == session_id)
            {
	        schedule.data[i].priority = max(expired_time, schedule.data[i].priority);
                return;
	    }
        }
	schedule.enqueue(session_id, expired_time);
}


string & session::operator [](char *s)
{
	return (*this)[string(s)];
}

string & session::operator [](string s)
{
	if (cache.empty())
	{
	    //error;
            return no_element;
	}
	mss::iterator itr = cache.find(s);
	if (itr == cache.end())
        {return no_element;}
	else 
	{
		return itr->second;
	}
}

void session::insert(string key, string value)
{
    cache[key] = value;
}

string session::newSession()
{
	cache.clear();
	string rname = generate_name();
	return rname;
}
