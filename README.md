# θ/β Ratio Calculator (t/b Ratio Calculator)

The  $\( \frac{θ}{β} \)$ ratio encapsulates the amplitude relationship between the theta \( θ \) and beta \( β \) frequency bands within the realm of EEG (Electroencephalogram) data.

## Mathematical Framework

Given a continuous time-domain EEG signal \( s(t) \), its transformation into the frequency domain is facilitated through the Fourier Transform:

$$
S(f) = \int_{-\infty}^{\infty} s(t) e^{-i 2 \pi f t} \, dt
$$

The processing pipeline to compute the  $\( \frac{θ}{β} \)$ ratio incorporates the following steps:

1. **Data Conversion:** 
    - Input data, represented as comma-separated strings, are parsed into vectors of doubles utilizing a bespoke function `convertStringToVector`.
    - The inverse operation is facilitated by the `convertVectorToString` function.

2. **Ferra's Filtering:**
    - A proprietary filtering technique named Ferra's filtering is applied to the theta, beta1, and beta2 data sets.
    - This method discerns and mitigates outliers based on a defined max limit, a multiple of the average, and a reduction factor to adjust extreme values, differing for theta and beta waves.
    - The Ferra's Filter operates under the following conditions in a sequential manner, only one of which will be applied:
        - If the maximum value in the data set surpasses a predefined max limit, it is set equal to the average value of the data set.
        - If the first condition hasn't been met and the maximum value exceeds a defined multiple of the average value, it is set equal to the average value of the data set.
        - If neither of the previous conditions have been met and the maximum value is greater than four times the average value, a reduction factor is applied to bring it closer to the average value.


3. **Additional Filtering:**
    - Various filters such as Exponential, Median, and Savitzky-Golay smoothing are employed to further refine the data.
    - These filters aid in smoothening the data, removing noise, interpolating missing values, and normalizing the data values.

4. **Average Computation:**
    - Post filtering, the averages of $\( θ \)$, $\( β₁ \)$, and $\( β₂ \)$ are computed.
    - The averages are calculated by summing all data points and dividing by the count of data points in each data set.

5. **Ratio Calculation:**
    -  The $\( \frac{θ}{β} \)$ ratio is ascertained through the formula:
   

    $$\frac{\theta}{\beta} = \frac{\theta}{[\beta_1 + (\beta_2/2)]}$$

           
    - Here, $\( θ \)$ symbolizes the mean amplitude of the theta band and \( β₁ \) and \( β₂ \)  the mean amplitudes of their respective frequency sub-bands.
    - The division of \( β₂ \) by 2 aims to balance its influence on the overall metric, addressing the typical artifact prevalence at the tail end of \( β₁ \) and the beginning of \( β₂ \) spectrum.

This comprehensive methodology ensures a robust computation of the $\( \frac{θ}{β} \)$ ratio, elucidating crucial insights into the EEG data and facilitating further neuroscientific analysis.


## Screenshot

![image](https://github.com/toniles/theta-beta-ratio/assets/120176462/afbb6e63-4b00-4cdb-87d2-6b6d157820ab)

## Download

Click [here](URL_OF_THE_FILE) to download the `.exe` file.

## Disclaimer

This tool is a mathematical representation and is not intended for the diagnosis, treatment, or prevention of any medical condition. Users should employ the software at their own risk and discretion. The developers and contributors bear no responsibility for any outcomes resulting from the use of this tool.

## License

This software is distributed under "The Unlicense". For a full understanding of what this entails, please refer to the accompanying `LICENSE` file or visit the official [Unlicense](https://unlicense.org/) website.

## Contributions and Feedback

For domain experts wishing to offer collaborations or feedback, please engage directly through the repository's structured systems.
