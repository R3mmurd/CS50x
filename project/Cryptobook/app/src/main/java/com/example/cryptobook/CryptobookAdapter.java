import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.cryptobook.R;

import java.util.Arrays;
import java.util.List;

public class CryptobookAdapter extends RecyclerView.Adapter<CryptobookAdapter.CryptobookViewHolder> {
    public class CryptobookViewHolder extends RecyclerView.ViewHolder {
        private LinearLayout containerView;
        // private ImageView imageView;
        private TextView textView;

        CryptobookViewHolder(View view) {
            super(view);

            containerView = view.findViewById(R.id.cryptobook_row);
            // imageView = view.findViewById(R.id.cryptobook_row_image_view);
            textView = view.findViewById(R.id.cryptobook_row_text_view);

            containerView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    // TODO
                }
            });
        }
    }


    List<Cryptocurrency> cryptocurrencies = Arrays.asList(
            new Cryptocurrency(1, "Ethereum", "BTC",
                    "https://s2.coinmarketcap.com/static/img/coins/64x64/1.png",
                    "https://bitcoin.org/"),
            new Cryptocurrency(1027, "Bitcoin", "ETH",
                    "https://s2.coinmarketcap.com/static/img/coins/64x64/1027.png",
                    "https://www.ethereum.org/")
    );

    @NonNull
    @Override
    public CryptobookViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.cryptobook_row, parent, false);
        return new CryptobookViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull CryptobookViewHolder holder, int position) {
        Cryptocurrency current = cryptocurrencies.get(position);
        holder.textView.setText(current.getName());
        holder.containerView.setTag(current);
    }

    @Override
    public int getItemCount() {
        return cryptocurrencies.size();
    }
}
