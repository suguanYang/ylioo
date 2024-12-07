import os

from haystack import Pipeline, Document
from haystack.utils import Secret
from haystack.document_stores.in_memory import InMemoryDocumentStore
from haystack.components.retrievers.in_memory import InMemoryBM25Retriever
from haystack.components.generators import OpenAIGenerator
from haystack.components.builders.answer_builder import AnswerBuilder
from haystack.components.builders.prompt_builder import PromptBuilder


# read documents from ./md/**/*.md
def create_document_store(path: str):
    document_store = InMemoryDocumentStore()
    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".md"):
                with open(os.path.join(root, file), "r") as f:
                    document_store.write_documents([Document(content=f.read(), id=os.path.join(root, file))])
    return document_store

def prompt_builder():
    themes = open("./prompts/markdown_themes.txt", "r").read()
    schema = open("./prompts/markdown_schema.txt", "r").read()
    constants = open("./prompts/constants.txt", "r").read()
    output = open("./prompts/output.txt", "r").read()
    return f'''
You are a markdown to html converter. you should translate the markdown content to html content.
By processing the input, you are given the context constants:
{constants}

You are given a common markdown schema:
{schema}

You are given themes:
{themes}

And your output should be in the following format:
{output}
'''

def main():
    document_store = create_document_store("./md")
    print(document_store)
    prompt = prompt_builder()
    print(prompt)

if __name__ == "__main__":
    main()


