#include "libLKYDeepNN/LKYDeepNN.hpp"
#include "libLKYDeepNN/DataSet.hpp"

void DrawTraining(LKYDeepNN* _nn, int maxEpochs, int currentEpochs, const vector<vector<double>>& displayData)
{   //size_t numItems = 80;
    string strPngName = "png/訓練途中" + to_string(currentEpochs) + ".png";
    string strPutText = "Epoch:"+to_string(currentEpochs)+"/"+to_string(maxEpochs)+"  Err:" + to_string(_nn->GetTrainError().back());

    //cv::imwrite(strPngName.c_str(),DrawData("訓練途中", displayData, strPutText));
    Draw2DRegressionData("訓練途中", displayData, _nn, strPutText);
    //fgetc(stdin);
}

int main()
{
    vector<vector<double>> trainData = WaveData();
    //int numHiddenNodesInEachLayer = 8;
    //int numHiddenLayers = 3;
    int numOutputLayer = 1;
    LKYDeepNN nn(trainData.front().size()-numOutputLayer, vector<int>{12,4,2}, numOutputLayer);
    nn.SetActivation(new Tanh(), new Linear());
    cout << nn.ToString() << endl;
    nn.eventInTraining = DrawTraining;//將包有視覺化的事件傳入

    cout << "訓練開始" <<endl;
    double learningRate = 0.005;
    int epochs = 900000;
    printf("learningRate=%lf\n",learningRate);
    nn.Training(learningRate, epochs, trainData);
    cout << nn.WeightsToString()<<endl;
    cout << "訓練完成" <<endl;
    cv::waitKey(0);
}