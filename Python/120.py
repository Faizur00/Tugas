from diagrams import Diagram, Edge
from diagrams.generic.blank import Blank
from diagrams.onprem.compute import Server
# from diagrams.onprem.ml import ML
from diagrams.programming.framework import Django
from diagrams.programming.language import Kotlin

with Diagram("Chatbot Pipeline", direction="LR"):
    data_sources = Blank("Data Sources\n(Medical Records, Textbooks)")
    preprocessing = Blank("Preprocessing\n(Cleaning, Integration, etc.)")
    training = ML("Model Training\n(Fine-Tuning BioBERT)")
    evaluation = Blank("Evaluation\n(Accuracy, F1-Score)")
    backend = Django("Backend\n(DRF API)")
    ui = Kotlin("User Interface\n(Kotlin Multiplatform)")

    data_sources >> preprocessing >> training >> evaluation >> backend >> ui
