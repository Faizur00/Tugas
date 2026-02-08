import requests
import json
from urllib.parse import quote

# === CONFIG ===
PAGE_ID = "278b1f28f44f8095ac95f59baeadaf15"  # Your page ID
PAGE_URL = f"https://www.notion.so/{PAGE_ID}"

HEADERS = {
    "accept": "application/json",
    "content-type": "application/json",
    "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36",
    "notion-client-version": "23.11.0.0",  # Important: mimic real client
}

session = requests.Session()

def get_space_id_and_load_page(page_id):
    # Step 1: Load the page chunk directly
    url = "https://www.notion.so/api/v3/loadPageChunk"
    payload = {
        "pageId": page_id,
        "limit": 100,
        "cursor": {"stack": []},
        "chunkNumber": 0,
        "verticalColumns": False
    }

    print("Fetching page chunk...")
    response = session.post(url, json=payload, headers=HEADERS)

    if response.status_code != 200:
        print(f"Failed: {response.status_code}")
        print(response.text)
        return None

    data = response.json()
    record_map = data.get("recordMap", {})

    # Extract title
    block = record_map.get("block", {}).get(page_id, {}).get("value", {})
    title = ""
    if block.get("properties", {}).get("title"):
        title = "".join([t[0] for t in block["properties"]["title"]])

    print(f"Title: {title}")

    # Extract all text content
    def extract_text_from_block(block_id, depth=0):
        if block_id not in record_map["block"]:
            return ""
        block = record_map["block"][block_id]["value"]
        text_parts = []

        # Get title/text
        if "properties" in block and "title" in block["properties"]:
            text = "".join([t[0] for t in block["properties"]["title"]])
            text_parts.append(text)

        # Recurse into child blocks
        for child_id in block.get("content", []):
            child_text = extract_text_from_block(child_id, depth + 1)
            if child_text:
                text_parts.append(child_text)

        return "\n".join(text_parts)

    content = extract_text_from_block(page_id)
    return {
        "title": title,
        "content": content,
        "raw": record_map  # optional: full JSON
    }

# === RUN ===
if __name__ == "__main__":
    result = get_space_id_and_load_page(PAGE_ID)
    if result:
        print("\n" + "="*50)
        print("SCRAPED CONTENT:")
        print("="*50)
        print(result["content"][:2000])  # First 2000 chars
        print("\n... (truncated)" if len(result["content"]) > 2000 else "")

        # Save to file
        with open("notion_page.txt", "w", encoding="utf-8") as f:
            f.write(f"TITLE: {result['title']}\n\n")
            f.write(result["content"])
        print("\nSaved to 'notion_page.txt'")