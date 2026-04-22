import feedparser
import os

def fetch_url(query):
    print(f"Util running, PID: {os.getpid()}")
    url = f"http://export.arxiv.org/api/query?search_query=all:{query}&max_results=1"
    feed = feedparser.parse(url)
    if feed.entries:
        entry = feed.entries[0]
        print("\nData Fetched")
        return entry
    else:
        print("No results")


