This repository utilizes Ollama and httplib to generate webpages on the fly whenever a request is made to the app.

For instance, visiting [serverurl]/contact will prompt the AI to generate a page based on the “/contact” path.

If you’re using Mac, you can download the prebuilt binary from the Releases section. Otherwise, follow these steps to build it manually:

## Building

### Prerequisites
* C++ 17
* Ollama
* g++ (recommended)

1. Start Ollama by executing the command:

``ollama serve``

2. Navigate to the “modelinfo” directory and build the “html_generator” model using Ollama. Run the following command:

``ollama create html_generator -f html_generator.modelfile``

3. Build the C++ file located in the root of this repository.

``g++ index.cpp -std=c++17 -o aigeneratedsite

4. Run the program by executing the following command:

``./aigeneratedsite``

The speed of the server will depend on the speed of your computer. If your computer cannot keep up, you can choose a lighter model by modifying the Modelfile FROM parameter.
