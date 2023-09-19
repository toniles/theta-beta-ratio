# theta-beta-ratio

# t/b Ratio Calculator

The ratio θ/β characterizes the amplitude relationship between the theta (θ) and beta (β) frequency bands in EEG (electroencephalogram) data.

## Mathematical Framework

Given a continuous time-domain EEG signal s(t), its transformation into the frequency domain is facilitated through the Fourier Transform:

S(f) = ∫_{-∞}^{∞} s(t) e^{-i 2 π f t} dt

To compute the θ/β ratio, the subsequent methodology is employed:

1. **Theta and Beta Wave Extraction:** From S(f), theta and beta wave components are extracted pursuant to the Fourier theorem. A typical standard involves examining, at the very least, 20 epochs, each spanning 2 seconds.

2. **EEG Recording Conditions:** It's pivotal to note that for an accurate representation of the θ and β activities, the EEG recording should be conducted with the eyes open while the subject engages in some form of cognitive activity. These conditions ensure that the EEG captures the dynamic interplay of the neural oscillations associated with the respective frequency bands.

3. **Artifact Exclusion:** Utmost diligence is imperative to ensure the omission of artifacts. One should circumvent impedances that yield artifacts within distinct frequency bands. Specific attention must be paid to the grounding and the calibration of the EEG system. It is paramount to ensure that the grounding electrode is well-connected to avoid electrical interference. Moreover, an appropriate calibration process before the EEG recording will ensure that the signals captured are reliable and free from external distortions.

4. **Beta Band Decomposition:** The β frequency is further decomposed into β1 and β2. In situations where a specific frequency within the β band manifests amplitude values that are anomalously elevated—surpassing a threshold of 10 times the average amplitude of the entire band (considering each specific frequency as a summative component like β1, β2, β2.1, and so on)—an averaging procedure is instituted. This procedure aims to attenuate the influence of outlier frequencies and ensure a balanced representation. The resultant value is then amalgamated into the summation.

5. **Frequency Summation:** All frequencies discerned through the FFT are aggregated to determine the mean amplitude for the respective frequency bands.

6. The θ/β ratio is subsequently ascertained through:

θ/β = θ/[β1 + (β2/2)]

Where θ symbolizes the mean amplitude of the theta band and β1 and β2 represent the mean amplitudes of their respective frequency sub-bands. The θ/β ratio seeks to represent equitably the contributions of the sub-bands β1 and β2 in the EEG. The division of β2 by 2 is a strategic mathematical choice to balance its influence on the overall metric. Theoretically, this adjustment could be derived from β2's susceptibility to experience more extreme amplitude variations or to be more prone to interference. By weighting β2 in this manner, the aim is to derive a metric that more accurately and holistically reflects the relationship between theta and beta activities, preventing β2 from dominating or distorting the ratio.

## 🖼️ Screenshots

![Screenshot 1](URL_IMAGEN_1)
![Screenshot 2](URL_IMAGEN_2)

## 📦 Download

Click [here](URL_OF_THE_FILE) to download the `.exe` file.

## ⚠️ Disclaimer

This tool is a mathematical representation and is not intended for the diagnosis, treatment, or prevention of any medical condition. Users should employ the software at their own risk and discretion. The developers and contributors bear no responsibility for any outcomes resulting from the use of this tool.

## 📜 License

This software is distributed under "The Unlicense". For a full understanding of what this entails, please refer to the accompanying `LICENSE` file or visit the official [Unlicense](https://unlicense.org/) website.

## 📢 Contributions and Feedback

For those well-versed in the domain wishing to offer collaborations or feedback, please engage directly through the repository's structured systems.
