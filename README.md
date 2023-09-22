# Theta-Beta Ratio Calculator (t/b Ratio Calculator)

The \( \theta/\beta \) ratio characterizes the amplitude relationship between the theta (\( \theta \)) and beta (\( \beta \)) frequency bands in EEG (electroencephalogram) data.

## Mathematical Framework

Given a continuous time-domain EEG signal \( s(t) \), its transformation into the frequency domain is facilitated through the Fourier Transform:

\[ S(f) = \int_{-\infty}^{\infty} s(t) e^{-i 2 \pi f t} \, dt \]

To compute the \( \theta/\beta \) ratio, the subsequent methodology is employed:

1. **Input Parsing:** A string containing comma-separated numbers is parsed into a list of numbers.
2. **Outlier Filtering:** Based on a proprietary filtering method, outliers are identified and excluded from further processing. The criteria for outlier identification is contingent on the mean value of the data and is delineated as follows:
    - If the mean is below 2, any number above 8.5 is considered an outlier.
    - If the mean is below 5, any number above 10 is considered an outlier.
    - If the mean is between 5 and 10, any number above 20 is considered an outlier.
    - If none of the aforementioned criteria are met, a median filter is applied for outlier detection.
    - If the total count of numbers is fewer than 4 post filtering, a blank average is returned.

3. **Average Computation:** Post outlier filtering, the averages of \( \theta \), \( \beta_1 \), and \( \beta_2 \) are computed.

4. **Ratio Calculation:** The \( \theta/\beta \) ratio is ascertained through the formula:
    \[ \theta/\beta = \theta / [\beta_1 + (\beta_2/2)] \]
    Where \( \theta \) symbolizes the mean amplitude of the theta band and \( \beta_1 \) and \( \beta_2 \) represent the mean amplitudes of their respective frequency sub-bands. The division of \( \beta_2 \) by 2 aims to balance its influence on the overall metric, addressing the typical artifact prevalence at the tail end of \( \beta_1 \) and the beginning of \( \beta_2 \) spectrum.

## Screenshot

![Screenshot 1](URL_IMAGEN_1)
![Screenshot 2](URL_IMAGEN_2)

## Download

Click [here](URL_OF_THE_FILE) to download the `.exe` file.

## Disclaimer

This tool is a mathematical representation and is not intended for the diagnosis, treatment, or prevention of any medical condition. Users should employ the software at their own risk and discretion. The developers and contributors bear no responsibility for any outcomes resulting from the use of this tool.

## License

This software is distributed under "The Unlicense". For a full understanding of what this entails, please refer to the accompanying `LICENSE` file or visit the official [Unlicense](https://unlicense.org/) website.

## Contributions and Feedback

For domain experts wishing to offer collaborations or feedback, please engage directly through the repository's structured systems.
