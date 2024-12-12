
function encodeBitmap(bitmap) {
    let runLengths = [];
    let currentColor = bitmap[0];  // Starting with the first color (0 for white, 1 for black)
    let currentLength = 1;

    // Step 1: Count all run lengths
    for (let i = 1; i < bitmap.length; i++) {
        if (bitmap[i] === currentColor) {
            currentLength++;
        } else {
            runLengths.push({ color: currentColor, length: currentLength });
            currentColor = bitmap[i];
            currentLength = 1;
        }
    }
    // Add the last run
    runLengths.push({ color: currentColor, length: currentLength });

    // Step 2: Ensure white is always first, and pair runs in alternating colors
    // If first run is black, add a 0-length white run
    if (runLengths[0].color === false) {
        runLengths.unshift({ color: true, length: 0 });
    }
    if (runLengths[runLengths.length-1].color === true) {
        runLengths.push({ color: false, length: 0 });
    }

    let pairedRuns = [];
    for (let i = 0; i < runLengths.length; i += 2) {
        let whiteRun = runLengths[i];   // odd indices: white
        let blackRun = runLengths[i + 1]; // even indices: black

        // If the run length exceeds limits, split it into smaller pairs
        if (whiteRun.length > 127) {
            while (whiteRun.length > 127) {
                pairedRuns.push([127, 0]);
                whiteRun.length -= 127;
            }
        } else if (blackRun.length > 255) {
            while (blackRun.length > 255) {
                pairedRuns.push([0, 255]);
                blackRun.length -= 255;
            }
        }

        pairedRuns.push([whiteRun.length, blackRun.length]);
    }

    // Step 3: Encode pairs
    let encodedBitmap = [];
    for (let i = 0; i < pairedRuns.length; i++) {
        const whiteLength = pairedRuns[i][0]
        const blackLength = pairedRuns[i][1]

        if (whiteLength < 8 && blackLength < 16) {
            // Use short run encoding
            const shortRun = (0 << 7) | (whiteLength << 4) | blackLength;
            encodedBitmap.push(shortRun);
        } else {
            // Use long run encoding
            const longRun = 1 << 7 | whiteLength;
            encodedBitmap.push(longRun, blackLength);
        }
    }
    console.log('bit pack:',Math.ceil(bitmap.length/8), 'compressed:', encodedBitmap.length, 'ratio:', (Math.ceil(bitmap.length/8)/encodedBitmap.length).toFixed(1))
    return encodedBitmap;
}

// Example usage
const bitmap = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1]; // A simple example
const encoded = encodeBitmap(bitmap).map(c=>c.toString(2).padStart(8,'0'));
console.log(encoded);
console.log(encoded.length, bitmap.length/8)