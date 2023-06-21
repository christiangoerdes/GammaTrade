import api from "../../../api/axiosConfig";
import { Buffer } from "buffer";
import { useEffect, useState } from "react";

export default function Graph(props) {
    const [imageBlob, setImageBlob] = useState(null);
    const [imageURL, setImageURL] = useState(null);

    const wholeImage = () => {
        api
        .get(`/get-stock-logged-out?stock=${props.stock.toLowerCase()}`)
        .then((response) => {
            setImageBlob(new Blob([Buffer.from(response.data.stock.plot, 'base64')], {type: 'image/png'}))
        })
        imageBlob && setImageURL(URL.createObjectURL(imageBlob))
    }

    useEffect(() => {
        const interval = setInterval(wholeImage, 3000);

        return () => {
            clearInterval(interval);
        }
    })
    
    return(
        <>
            {imageURL ? <img src={imageURL} alt="plot" /> : <div>Image Loading...</div>}
        </>
    )
}
