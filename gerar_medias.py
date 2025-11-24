import zipfile
import pandas as pd
import os
import sys

def calcular_media_zip_obj_por_tempo(zip_obj):
    """Calcula médias por instante de tempo entre vários CSVs dentro do zip."""
    csvs = [name for name in zip_obj.namelist() if name.lower().endswith(".csv")]

    if not csvs:
        raise ValueError("Nenhum CSV encontrado dentro do ZIP.")

    dfs = []
    for csv_name in csvs:
        with zip_obj.open(csv_name) as csv_file:
            df = pd.read_csv(csv_file)

            # Garantir que Tempo decorrido é string
            df["Tempo decorrido"] = df["Tempo decorrido"].astype(str)
            dfs.append(df)

    # Junta todos os CSVs empilhados
    df_all = pd.concat(dfs, ignore_index=True)

    # Agrupar por tempo e tirar média das colunas numéricas
    df_media_por_tempo = (
        df_all.groupby("Tempo decorrido")
              .mean(numeric_only=True)
              .reset_index()
    )

    if "Erro Little" in df_media_por_tempo.columns:
        df_media_por_tempo["Erro Little"] = df_media_por_tempo["Erro Little"].apply(
            lambda x: f"{x:.20f}"
        )

    return df_media_por_tempo


def processar_zip_geral(zip_geral_path, output_dir="medias"):
    """Processa o ZIP geral e gera um CSV médio para cada sub-ZIP."""
    # Criar pasta de saída
    os.makedirs(output_dir, exist_ok=True)

    print(f"🔍 Abrindo ZIP geral: {zip_geral_path}")
    with zipfile.ZipFile(zip_geral_path, 'r') as outer_zip:

        # Descobrir os ZIPs internos
        inner_zips = [n for n in outer_zip.namelist() if n.lower().endswith(".zip")]

        if not inner_zips:
            raise ValueError("Nenhum ZIP interno encontrado no ZIP geral.")

        print(f"📦 Encontrados {len(inner_zips)} grupos:")
        for nz in inner_zips:
            print("   →", nz)

        # Processar cada ZIP interno
        for inner_name in inner_zips:
            print(f"\n➡ Processando grupo '{inner_name}'...")

            # Abrir o ZIP interno diretamente em memória
            with outer_zip.open(inner_name) as inner_file:
                with zipfile.ZipFile(inner_file) as inner_zip:
                    df_media = calcular_media_zip_obj_por_tempo(inner_zip)


            # Nome do CSV de saída
            output_csv_name = inner_name.replace(".zip", "_media.csv")
            output_path = os.path.join(output_dir, output_csv_name)

            # Salvar
            df_media.to_csv(output_path, index=False)

            print(f"   ✔ Média salva em: {output_path}")

    print("\n✨ Concluído! Todos os arquivos estão na pasta:", output_dir)


# --------------------------
# Execução via linha de comando
# --------------------------
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python gerar_medias.py <arquivo.zip> [saida]")
        sys.exit(1)

    zip_geral_path = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) >= 3 else "medias"

    processar_zip_geral(zip_geral_path, output_dir)
